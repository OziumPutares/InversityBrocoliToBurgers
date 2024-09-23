// Utility function to parse required search terms from a line
function ParseRequiredSearchTermLine(line) {
    if (line.startsWith('!') || line.startsWith('#') || line.trim() === '') {
        return ''; // Empty string for lines with comments or invalid data
    }
    return line.split('!')[0]; // Return part of the line before '!'
}

// Utility function to parse forbidden terms (unsafe version)
function ParseForbiddenSearchTermUnsafe(line) {
    const searchTermList = [];
    const parts = line.split('!'); // Split by '!'
    for (let i = 1; i < parts.length; i++) {  // Skip the first part before the '!'
        searchTermList.push(parts[i]);
    }
    return searchTermList;
}

// Parse forbidden terms from a line safely
function ParseForbiddenSearchTermLine(line) {
    if (line.startsWith('#') || !line.includes('!')) {
        return []; // Return empty array if no forbidden terms present
    }
    return ParseForbiddenSearchTermUnsafe(line);
}

// Class representing a required search term
class RequiredTerm {
    constructor(line) {
        this.RequiredTerm_ = ParseRequiredSearchTermLine(line);
    }

    containsRequiredTerm(val) {
        return val.includes(this.RequiredTerm_);
    }
}

// Class representing a single forbidden term
class ForbiddenTerm {
    constructor(line, indexOfForbiddenTerm = 0) {
        // Parse forbidden terms from the line
        const output = ParseForbiddenSearchTermLine(line);

        // Ensure the index is within bounds
        if (indexOfForbiddenTerm >= output.length) {
            console.warn(
                `indexOfForbiddenTerm (${indexOfForbiddenTerm}) is out of range. Available forbidden terms: ${output}`
            );
            this.ForbiddenTerm_ = ''; // Set to empty string to avoid errors
        } else {
            this.ForbiddenTerm_ = output[indexOfForbiddenTerm];
        }
    }

    containsForbiddenTerm(val) {
        // Check if the forbidden term exists in the string
        return this.ForbiddenTerm_ && val.includes(this.ForbiddenTerm_);
    }
}

// Class representing multiple forbidden terms
class ForbiddenTerms {
    constructor(line) {
        this.ForbiddenTerms_ = [];
        const forbiddenTokens = ParseForbiddenSearchTermLine(line);

        if (forbiddenTokens.length === 0) {
            console.warn(`No forbidden terms found in line: ${line}`);
        } else {
            forbiddenTokens.forEach(token => {
                this.ForbiddenTerms_.push(new ForbiddenTerm(token));
            });
        }
    }

    containsAForbiddenTerm(strToCheck) {
        return this.ForbiddenTerms_.some(term => term.containsForbiddenTerm(strToCheck));
    }
}

// Config class to load and filter data from a configuration file
class Config {
    constructor(fileName) {
        this.FilterList_ = [];

        // Simulating reading a config file line-by-line
        const lines = fileName.split('\n'); // Assuming fileName is the file content passed in as a string
        lines.forEach(line => {
            if (line.trim()) {  // Ignore empty lines
                this.FilterList_.push([new RequiredTerm(line), new ForbiddenTerms(line)]);
            }
        });
    }

    filterList(fileContent) {
        let filteredList = '';

        const lines = fileContent.split('\n');
        lines.forEach(line => {
            for (const [requiredTerm, forbiddenTerms] of this.FilterList_) {
                if (requiredTerm.containsRequiredTerm(line) && !forbiddenTerms.containsAForbiddenTerm(line)) {
                    filteredList += line + '\n';
                }
            }
        });

        return filteredList;
    }
}

// Export the Config class for use in other files
//export { Config };

