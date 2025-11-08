// ===== CONFIGURATION =====
const CURRENT_DAY = 8; // Update this when adding new days

// Handle search functionality
function handleSearch() {
    const input = document.getElementById('searchInput');
    const messageDiv = document.getElementById('searchMessage');
    const dayNum = parseInt(input.value);
    
    if (!dayNum || dayNum < 1) {
        showMessage('Please enter a valid day number', 'error');
        input.value = '';
        return;
    }

    if (dayNum > CURRENT_DAY) {
        showMessage(`I haven't reached day ${dayNum} yet! Currently on day ${CURRENT_DAY}.`, 'error');
        input.value = '';
    } else {
        showMessage(`Redirecting to Day ${dayNum}...`, 'success');
        input.value = ''; // Clear input immediately after successful validation
        setTimeout(() => {
            window.location.href = `Journal-and-Approaches/day${dayNum}.html`;
        }, 800);
    }
}

// Show message to user
function showMessage(message, type) {
    const messageDiv = document.getElementById('searchMessage');
    messageDiv.textContent = message;
    messageDiv.className = `message ${type}`;
}

// Add event listener for Enter key and button click
document.addEventListener('DOMContentLoaded', function() {
    const searchInput = document.getElementById('searchInput');
    const searchButton = document.querySelector('.search-container button');
    
    // Enter key support
    searchInput.addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            handleSearch();
        }
    });
    
    // Button click (you can remove onclick from HTML if using this)
    searchButton.addEventListener('click', handleSearch);
    
    // Update progress stats
    document.getElementById('daysCount').textContent = CURRENT_DAY;
    document.getElementById('daysStrong').textContent = CURRENT_DAY;
    
    // Auto-focus on search input
    searchInput.focus();
});