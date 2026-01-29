document.querySelectorAll('form').forEach(form => {
    form.addEventListener('submit', async event => {
        event.preventDefault();
        const response = await fetch(form.action, { method: 'POST' });
        if (response.ok) {
            const newMode = await response.text();
            document.getElementById('currentMode').textContent = newMode;
        }
    });
});
