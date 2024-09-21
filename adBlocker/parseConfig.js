// Utility function to parse required search terms from a line
function ParseRequiredSearchTermLine(line) {
    if (line.startsWith('!') || line.startsWith('#') || line.trim() === '') {
        return '';
    }
    return line.split('!')[0];  // Extract part before "!"
}

// Utility function to parse forbidden search terms from a line (unsafe version)
function ParseForbiddenSearchTermUnsafe(line) {
    let tokens = line.split('!');
    tokens.shift();  // Remove the first part (before the first "!")
    return tokens;   // Return the rest as forbidden terms
}

// Safe version of parsing forbidden search terms, skipping comments or lines without "!"
function ParseForbiddenSearchTermLine(line) {
    if (line.startsWith('#') || !line.includes('!')) {
        return [];
    }
    return ParseForbiddenSearchTermUnsafe(line);
}

// Class representing a Required Term
function RequiredTerm(line) {
    this.requiredTerm = ParseRequiredSearchTermLine(line);

    // Method to check if a line contains the required term
    this.ContainsRequiredTerm = function (val) {
        return val.includes(this.requiredTerm);
    };
}

// Class representing a Forbidden Term
function ForbiddenTerm(line, indexOfForbiddenTerm = 0) {
    let output = ParseForbiddenSearchTermLine(line);

    if (indexOfForbiddenTerm >= output.length) {
        throw new Error('indexOfForbiddenTerm is out of range');
    }

    this.forbiddenTerm = output[indexOfForbiddenTerm];

    // Method to check if a line contains the forbidden term
    this.ContainsForbiddenTerm = function (val) {
        return val.includes(this.forbiddenTerm);
    };
}

// Class representing multiple Forbidden Terms
function ForbiddenTerms(line) {
    this.forbiddenTerms = [];

    // Populate the forbidden terms list from the line
    let forbiddenTokens = ParseForbiddenSearchTermLine(line);
    for (let token of forbiddenTokens) {
        this.forbiddenTerms.push(new ForbiddenTerm(token));
    }

    // Method to check if any forbidden term is contained in the given string
    this.ContainsAForbiddenTerm = function (strToCheck) {
        return this.forbiddenTerms.some(function (term) {
            return term.ContainsForbiddenTerm(strToCheck);
        });
    };
}

// Class representing the configuration, loading required and forbidden terms from a file
function Config(configContent) {
    this.filterList = [];

    // Parse the config file content line by line
    let lines = configContent.split('\n');
    for (let line of lines) {
        if (line.trim() !== '') {
            this.filterList.push([new RequiredTerm(line), new ForbiddenTerms(line)]);
        }
    }

    // Method to filter a list of lines (configurable search terms) based on the loaded rules
    this.FilterList = function (fileContent) {
        let filteredList = '';
        let lines = fileContent.split('\n');

        for (let line of lines) {
            for (let filterEntry of this.filterList) {
                let [requiredTerm, forbiddenTerms] = filterEntry;
                
                // Apply filtering: Check for required terms and no forbidden terms
                if (requiredTerm.ContainsRequiredTerm(line) && !forbiddenTerms.ContainsAForbiddenTerm(line)) {
                    filteredList += line + '\n';
                }
            }
        }
        return filteredList;
    };
}
