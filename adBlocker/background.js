// Compatibility layer for chrome.storage.local (for Firefox and Chrome)
let storage;
if (typeof browser !== "undefined" && browser.storage) {
    storage = browser.storage.local;  // Firefox
} else if (typeof chrome !== "undefined" && chrome.storage) {
    storage = chrome.storage.local;  // Chrome
} else {
    console.error("Storage API is not available.");
}

// Ensure storage is available before proceeding
if (storage) {
    const EASYLIST_URL = 'https://easylist.to/easylist/easylist.txt';
    const CACHE_KEY = 'easylist_cache';
    const CACHE_TIMESTAMP_KEY = 'easylist_timestamp';
    const ONE_DAY = 24 * 60 * 60 * 1000; // 1 day in milliseconds

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
                console.warn(`Skipped invalid domain (no valid TLD): ${domain}`);
                return;
            }

            const urlPattern = `*://*.${domain}/*`;

            // Validate the generated URL pattern and ensure it matches allowed formats
            if (urlPatternRegex.test(urlPattern)) {
                blockList.push(urlPattern);
            } else {
                console.warn(`Skipped invalid URL pattern: ${urlPattern}`);
            }
        }
    });

    // Log all patterns before returning
    console.log('Final block list:', blockList);

    return blockList;
}




    function fetchAndCacheEasyList() {
        return fetch(EASYLIST_URL)
            .then(response => response.text())
            .then(data => {
                const blockList = parseEasyList(data);
                const now = Date.now();

                // Store the list and timestamp in storage (either chrome or browser)
                storage.set({ [CACHE_KEY]: blockList, [CACHE_TIMESTAMP_KEY]: now });

                return blockList;
            });
    }

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

    // Fetch the EasyList and start blocking ads
    getEasyList().then(blockList => {
        chrome.webRequest.onBeforeRequest.addListener(
            function(details) {
                console.log("Blocking request to: " + details.url);
                return { cancel: true };
            },
            { urls: blockList },
            ["blocking"]
        );
    }).catch(error => console.error('Error loading EasyList:', error));
} else {
    console.error("Storage API is not available.");
}

