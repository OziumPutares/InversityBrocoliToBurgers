// Define constants for EasyList URL and storage keys
const EASYLIST_URL = 'https://easylist.to/easylist/easylist.txt';
const CACHE_KEY = 'easylist_cache';
const CACHE_TIMESTAMP_KEY = 'easylist_timestamp';
const ONE_DAY = 24 * 60 * 60 * 1000; // 1 day in milliseconds

// Compatibility layer for chrome.storage.local (for Firefox and Chrome)
let storage;
if (typeof browser !== "undefined" && browser.storage) {
    storage = browser.storage.local;  // Firefox
} else if (typeof chrome !== "undefined" && chrome.storage) {
    storage = chrome.storage.local;  // Chrome
} else {
    console.error("Storage API is not available.");
}

// Function to parse EasyList and convert it to a list of blocking patterns
function parseEasyList(list) {
    const lines = list.split('\n');
    const blockList = [];

    // Regex to match valid domains with proper TLDs (e.g., *.example.com/*)
    const validTldRegex = /\.(com|net|org|io|edu|gov|co|uk|us|de|fr|ca|au|jp|cn|xyz|mobi)$/;
    const urlPatternRegex = /^\*:\/\/\*\.[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)+\/\*$/;

    lines.forEach(line => {
        // Skip comments and empty lines
        if (line.startsWith('!') || line.trim() === '') {
            return;
        }

        if (line.startsWith('||')) {
            let domain = line.split('^')[0].substring(2);  // Extract the domain

            // Validate that the domain contains a valid TLD
            if (!validTldRegex.test(domain)) {
                console.log(`Skipped invalid domain (no valid TLD): ${domain}`);
                return;
            }

            const urlPattern = `*://*.${domain}/*`;

            // Validate the generated URL pattern and ensure it matches allowed formats
            if (urlPatternRegex.test(urlPattern)) {
                blockList.push(urlPattern);
            } else {
                console.log(`Skipped invalid URL pattern: ${urlPattern}`);
            }
        }
    });

    // Log all patterns before returning
    console.log('Final block list:', blockList);

    return blockList;
}

// Fetch EasyList from the remote URL and cache it in storage
function fetchAndCacheEasyList() {
    return fetch(EASYLIST_URL)
        .then(response => response.text())
        .then(data => {
            const blockList = parseEasyList(data);
            const now = Date.now();

            // Store the list and timestamp in storage
            storage.set({ [CACHE_KEY]: blockList, [CACHE_TIMESTAMP_KEY]: now });

            return blockList;
        });
}

// Retrieve the EasyList from storage, or fetch and cache it if expired
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

// Load the local config file and create a Config object
function loadConfigFile(configFileName) {
    return fetch(configFileName)
        .then(response => {
            if (!response.ok) {
                throw new Error(`Failed to load config file: ${response.statusText}`);
            }
            return response.text();
        })
        .then(configContent => {
            const config = new Config(configContent);  // Config class from parseConfig.js
            return config;
        })
        .catch(error => {
            console.error(error);
            return null;
        });
}

// Initialize the blocking system by applying the EasyList and config filters
function initializeBlocking() {
    const configFileName = './config.txt';  // Local config file

    // Load the EasyList and config file
    Promise.all([getEasyList(), loadConfigFile(configFileName)])
        .then(([easyList, config]) => {
            if (config) {
                console.log('Config loaded successfully');

                // Filter EasyList through the Config filtering mechanism
                const filteredBlockList = config.filterList(easyList.join('\n')).split('\n').filter(Boolean);

                console.log('Filtered block list:', filteredBlockList);

                // Start blocking requests using the filtered block list
                chrome.webRequest.onBeforeRequest.addListener(
                    function(details) {
                        console.log("Blocking request to: " + details.url);
                        return { cancel: true };
                    },
                    { urls: filteredBlockList },
                    ["blocking"]
                );
            } else {
                console.error('Failed to load config file');
            }
        })
        .catch(error => {
            console.error('Error initializing ad blocker:', error);
        });
}

// Ensure storage is available before proceeding
if (storage) {
    initializeBlocking();  // Start the ad blocker
} else {
    console.error("Storage API is not available.");
}

