// ===== CONFIGURATION - UPDATE THIS ONE NUMBER =====
const CURRENT_DAY = 4; // ⬅️ ONLY CHANGE THIS WHEN ADDING NEW DAYS

// Problem mapping configuration
const PROBLEM_CONFIG = {
    OFFSET: 12, // Day 1 = Problem 13 (1 + 12)
    
    // Only for true exceptions to the pattern
    manualOverrides: {
        // Example: if you ever break the pattern
        // 5: 20,  // Day 5 would be Problem 20 instead of 17
    }
};

// ===== AUTO-GENERATED CONFIGURATION =====
const AVAILABLE_DAYS = Array.from({length: CURRENT_DAY}, (_, i) => i + 1);

// Convert day number to problem number
function dayToProblem(day) {
    if (PROBLEM_CONFIG.manualOverrides[day]) {
        return PROBLEM_CONFIG.manualOverrides[day];
    }
    return day + PROBLEM_CONFIG.OFFSET;
}

// Convert problem number to day number
function problemToDay(problem) {
    // Check manual overrides first
    for (const [day, prob] of Object.entries(PROBLEM_CONFIG.manualOverrides)) {
        if (prob === problem) {
            return parseInt(day);
        }
    }
    return problem - PROBLEM_CONFIG.OFFSET;
}

// Check if a day exists
function dayExists(day) {
    return day >= 1 && day <= CURRENT_DAY;
}

// Check if a problem exists
function problemExists(problem) {
    const day = problemToDay(problem);
    return dayExists(day) && dayToProblem(day) === problem;
}

// Handle search functionality
// Handle search functionality
function handleSearch() {
    const searchType = document.getElementById('searchType').value;
    const inputValue = document.getElementById('searchInput').value.trim();
    const messageDiv = document.getElementById('searchMessage');
    
    if (!inputValue) {
        showMessage(`Please enter a ${searchType} number`, 'error');
        return;
    }

    const inputNum = parseInt(inputValue);
    
    if (inputNum < 1) {
        showMessage('Please enter a positive number', 'error');
        return;
    }

    if (searchType === 'day') {
        // Search by day number
        if (inputNum > CURRENT_DAY) {
            showMessage(`I haven't reached day ${inputNum} yet! Currently on day ${CURRENT_DAY}.`, 'error');
        } else {
            const problemNum = dayToProblem(inputNum);
            showMessage(`Redirecting to Day ${inputNum} (Problem ${problemNum})...`, 'success');
            setTimeout(() => {
                window.location.href = `Journal-and-Approaches/day${inputNum}.html`;
            }, 800);
        }
    } else {
        // Search by problem number
        const dayNum = problemToDay(inputNum);
        
        if (problemExists(inputNum)) {
            showMessage(`Redirecting to Problem ${inputNum} (Day ${dayNum})...`, 'success');
            setTimeout(() => {
                window.location.href = `Journal-and-Approaches/day${dayNum}.html`;
            }, 800);
        } else {
            // Check if it's a future problem
            const currentProblem = dayToProblem(CURRENT_DAY);
            if (inputNum > currentProblem) {
                showMessage(`Problem ${inputNum} is not available yet. Currently on Problem ${currentProblem}.`, 'error');
            } else {
                showMessage(`Problem ${inputNum} is not available.`, 'error');
            }
        }
    }
}

// Show message to user
function showMessage(message, type) {
    const messageDiv = document.getElementById('searchMessage');
    messageDiv.innerHTML = message;
    messageDiv.className = `message ${type}`;
}

// Initialize the page
function initializePage() {
    // Update progress stats
    document.getElementById('daysCount').textContent = CURRENT_DAY;
    document.getElementById('daysStrong').textContent = CURRENT_DAY;
    
    // Update next goal (every 10 problems)
    const nextGoal = Math.ceil((CURRENT_DAY + 1) / 10) * 10;
    document.getElementById('nextGoal').textContent = nextGoal;
    
    // Populate problems list (show last 7-10 problems)
    const problemsList = document.getElementById('problemsList');
    problemsList.innerHTML = '';
    
    const startDay = Math.max(1, CURRENT_DAY - 9); // Show max 10 days
    const recentDays = AVAILABLE_DAYS.slice(startDay - 1).reverse();
    
    recentDays.forEach(day => {
        const problemNum = dayToProblem(day);
        const li = document.createElement('li');
        li.innerHTML = `<a href="Journal-and-Approaches/day${day}.html">Day ${day}: Problem ${problemNum}</a>`;
        problemsList.appendChild(li);
    });
    
    // Show "View Archive" link if more than 10 days
    if (CURRENT_DAY > 10) {
        const li = document.createElement('li');
        li.innerHTML = `<a href="archive.html" style="font-style: italic;">View archive (${CURRENT_DAY} problems)...</a>`;
        problemsList.appendChild(li);
    }
    
    // Add Enter key support for search
    document.getElementById('searchInput').addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            handleSearch();
        }
    });
    
    // Auto-focus on search input
    document.getElementById('searchInput').focus();
    
    // Update placeholder based on selection
    document.getElementById('searchType').addEventListener('change', function() {
        const placeholder = this.value === 'day' ? 'Enter day number' : 'Enter problem number';
        document.getElementById('searchInput').placeholder = placeholder;
    });
}

// Initialize when page loads
document.addEventListener('DOMContentLoaded', initializePage);
