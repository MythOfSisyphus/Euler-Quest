// Copy Code Functionality
document.addEventListener('DOMContentLoaded', function() {
    // Add event listeners to all copy buttons
    const copyButtons = document.querySelectorAll('.copy-btn');
    
    copyButtons.forEach(button => {
        button.addEventListener('click', function() {
            const codeContainer = this.parentElement;
            const codeElement = codeContainer.querySelector('code');
            const code = codeElement.textContent;
            
            navigator.clipboard.writeText(code).then(() => {
                const originalText = this.textContent;
                this.textContent = 'Copied!';
                setTimeout(() => {
                    this.textContent = originalText;
                }, 2000);
            }).catch(err => {
                console.error('Failed to copy code: ', err);
                this.textContent = 'Failed!';
                setTimeout(() => {
                    this.textContent = 'Copy';
                }, 2000);
            });
        });
    });
});