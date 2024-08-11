function showLinuxPopup() {
    document.getElementById("linuxPopup").style.display = "block";
}

function closeLinuxPopup() {
    document.getElementById("linuxPopup").style.display = "none";
}

function showComingSoon() {
    document.getElementById("comingSoonPopup").style.display = "block";
}

function closeComingSoonPopup() {
    document.getElementById("comingSoonPopup").style.display = "none";
}

function sourceCode() {
    window.location.href = "../dl404.html";
}


function downloadWindows() {
    // Redirect to the Windows download link
    window.location.href = "../dl404.html";
}

function loadReleaseNotes() {
    fetch('changes.md')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok: ' + response.statusText);
            }
            return response.text();
        })
        .then(text => {
            const converter = new showdown.Converter();
            document.getElementById('release-notes').innerHTML = converter.makeHtml(text);
        })
        .catch(error => {
            console.error('Error loading release notes:', error);
            document.getElementById('release-notes').innerHTML = '<p>Error loading release notes.</p>';
        });
}

// Load release notes on page load
window.onload = function() {
    loadReleaseNotes();
};