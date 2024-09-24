//import { Config } from './parseConfig.js';

// Compatibility layer for chrome.storage.local (for Firefox and Chrome)
let storage;
if (typeof browser !== "undefined" && browser.storage) {
    storage = browser.storage.local;  // Firefox
} else if (typeof chrome !== "undefined" && chrome.storage) {
    storage = chrome.storage.local;  // Chrome
} else {
    console.error("Storage API is not available.");
}

// EasyList URL and caching keys
const EASYLIST_URL = 'https://easylist.to/easylist/easylist.txt';
const CACHE_KEY = 'easylist_cache';
const CACHE_TIMESTAMP_KEY = 'easylist_timestamp';
const ONE_DAY = 24 * 60 * 60 * 1000; // 1 day in milliseconds

// Function to parse EasyList
function parseEasyList(list) {
    const lines = list.split('\n');
    const blockList = [];
    const validTldRegex = /\.(com|net|org|io|edu|gov|co|uk|us|de|fr|ca|au|jp|cn|xyz|mobi)$/;
    const urlPatternRegex = /^\*:\/\/\*\.[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)+\/\*$/;

    lines.forEach(line => {
        if (line.startsWith('!') || line.trim() === '') {
            return; // Skip comments and empty lines
        }

        if (line.startsWith('||')) {
            const domain = line.split('^')[0].substring(2);
            if (validTldRegex.test(domain)) {
                const urlPattern = `*://*.${domain}/*`;
                if (urlPatternRegex.test(urlPattern)) {
                    blockList.push(urlPattern);
                }
            }
        }
    });

    console.log('Parsed block list:', blockList); // Debugging log
    return blockList;
}

// Fetch and cache EasyList
function fetchAndCacheEasyList() {
    return fetch(EASYLIST_URL)
        .then(response => response.text())
        .then(data => {
            const blockList = parseEasyList(data);
            const now = Date.now();
            storage.set({ [CACHE_KEY]: blockList, [CACHE_TIMESTAMP_KEY]: now });
            return blockList;
        });
}

// Get EasyList from storage or fetch
function getEasyList() {
    return new Promise((resolve, reject) => {
        storage.get([CACHE_KEY, CACHE_TIMESTAMP_KEY], (items) => {
            const now = Date.now();
            if (!items[CACHE_KEY] || !items[CACHE_TIMESTAMP_KEY] || (now - items[CACHE_TIMESTAMP_KEY] > ONE_DAY)) {
                fetchAndCacheEasyList().then(resolve).catch(reject);
            } else {
                resolve(items[CACHE_KEY]);
            }
        });
    });
}

// Main execution
function fetchConfigFile() {
    return fetch(chrome.runtime.getURL('config.txt'))
        .then(response => response.text())
        .catch(error => {
            console.error('Error fetching config.txt:', error);
            return ''; // Return an empty string if there's an error
        });
}

// Main execution
Promise.all([getEasyList(), fetchConfigFile()])
    .then(([blockList, configFileContent]) => {
        const config = new Config(configFileContent);  // Use the fetched config file
        const filteredList = config.filterList(blockList.join('\n')).split('\n').filter(pattern => pattern);

        console.log('Filtered block list:', filteredList);

        if (filteredList.length > 0) {
            chrome.webRequest.onBeforeRequest.addListener(
                function(details) {
                    console.log("Blocking request to: " + details.url);
                    return { cancel: true };
                },
                { urls: filteredList },
                ["blocking"]
            );
        } else {
            console.warn('No valid URL patterns to block.');
        }
    })
    .catch(error => console.error('Error initializing ad blocker:', error));
