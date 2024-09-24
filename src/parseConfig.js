// Utility function to parse required search terms from a line
function parseRequiredSearchTerm(line) {
    if (isCommentOrEmpty(line)) return ''; // Early return for invalid lines
    return line.split('!')[0].trim(); // Return part of the line before '!'
}

// Utility function to parse forbidden terms from a line
function parseForbiddenSearchTerms(line) {
    if (isCommentOrEmpty(line)) return [];
    return line.split('!').slice(1).map(term => term.trim()); // Get terms after the first '!'
}

// Check if a line is a comment or empty
function isCommentOrEmpty(line) {
    return line.startsWith('!') || line.startsWith('#') || line.trim() === '';
}

// Class representing a single required term
class RequiredTerm {
    constructor(term) {
        this.term = term;
    }

    // Check if the required term is present in the provided value
    containsIn(value) {
        return this.term && value.includes(this.term);
    }
}

// Class representing a single forbidden term
class ForbiddenTerm {
    constructor(term) {
        this.term = term;
    }

    // Check if the forbidden term is present in the provided value
    containsIn(value) {
        return this.term && value.includes(this.term);
    }
}

// Class representing multiple forbidden terms
class ForbiddenTerms {
    constructor(terms) {
        this.terms = terms.map(term => new ForbiddenTerm(term));
    }

    // Check if any forbidden term is present in the provided value
    containsAny(value) {
        return this.terms.some(term => term.containsIn(value));
    }
}

// Class representing a single filter rule combining required and forbidden terms
class FilterRule {
    constructor(requiredTerm, forbiddenTerms) {
        this.requiredTerm = new RequiredTerm(requiredTerm);
        this.forbiddenTerms = new ForbiddenTerms(forbiddenTerms);
    }

    // Check if the value matches the required term and does not contain forbidden terms
    isMatch(value) {
        return this.requiredTerm.containsIn(value) && !this.forbiddenTerms.containsAny(value);
    }
}

// Class to manage configuration and filtering
class Config {
    constructor(fileContent) {
        this.filterRules = this.parseConfig(fileContent); // SRP: Parse rules
    }

    // Parse the config content and create filter rules
    parseConfig(content) {
        const lines = content.split('\n').filter(line => line.trim());
        return lines.map(line => {
            const requiredTerm = parseRequiredSearchTerm(line);
            const forbiddenTerms = parseForbiddenSearchTerms(line);
            return new FilterRule(requiredTerm, forbiddenTerms); // Create a FilterRule for each line
        });
    }

    // Delegate filtering responsibility to LineProcessor
    filterList(content) {
        const processor = new LineProcessor(this.filterRules);
        return processor.processLines(content); // Use the LineProcessor to apply the filtering
    }
}

// Class to process lines and apply filter rules
class LineProcessor {
    constructor(filterRules) {
        this.filterRules = filterRules;
    }

    // Process each line and apply the rules to filter
    processLines(content) {
        return content.split('\n').filter(line => this.applyRules(line)).join('\n').trim();
    }

    // Apply all rules to a single line
    applyRules(line) {
        for (const rule of this.filterRules) {
            if (rule.isMatch(line)) {
                return true; // Return true if a rule matches
            }
        }
        return false; // Return false if no rule matches
    }
}

// Export the Config class for use in other files
//export { Config };

