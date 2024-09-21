// Ensure parseConfig.js is included first in manifest.json (under scripts) so functions are available

// Compatibility layer for chrome.storage.local (for Firefox and Chrome)
let storage;
if (typeof browser !== "undefined" && browser.storage) {
    storage = browser.storage.local;  // Firefox
} else if (typeof chrome !== "undefined" && chrome.storage) {
    storage = chrome.storage.local;  // Chrome
} else {
    console.error("Storage API is not available.");
}

// Load config file using fetch instead of fs
function loadConfigFile(configFileName) {
    return fetch(configFileName)
        .then(response => {
            if (!response.ok) {
                throw new Error(`Failed to load config file: ${response.statusText}`);
            }
            return response.text();
        })
        .then(configContent => {
            // Use the Config class from parseConfig.js
            const config = new Config(configContent);
            return config;
        })
        .catch(error => {
            console.error(error);
            return null;
        });
}

// Usage example: Load the config.txt file
const configFileName = './config.txt';
loadConfigFile(configFileName).then(config => {
    if (config) {
        console.log('Config object loaded successfully:', config);
    }
});

// The rest of your background.js logic follows here...