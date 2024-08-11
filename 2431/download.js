let countdownTimer;
let countdownValue = 10; // Starting value for countdown
let downloadUrl = ''; // To store the download URL

function showCountdownPopup(callback) {
    document.getElementById("countdownPopup").style.display = "block";
    const countdownElement = document.getElementById("countdown");
    countdownElement.textContent = countdownValue;

    countdownTimer = setInterval(() => {
        countdownValue--;
        countdownElement.textContent = countdownValue;
        if (countdownValue <= 0) {
            clearInterval(countdownTimer);
            document.getElementById("countdownPopup").style.display = "none";
            callback(); // Execute the callback function to start the download
        }
    }, 1000);
}

function closeCountdownPopup() {
    clearInterval(countdownTimer); // Stop the countdown if the popup is closed
    document.getElementById("countdownPopup").style.display = "none";
}

function closeLinuxPopup() {
    document.getElementById("linuxPopup").style.display = "none";
}

function startLinuxDownload(version) {
    // Set the appropriate download URL based on the version
    switch (version) {
        case 'deb':
            downloadUrl = 'https://github.com/DanielLMcGuire/Source-Search/releases/download/1.2.5/sourcesearch_x86_64_1.2.5.deb';
            break;
        case 'pkg':
            downloadUrl = 'https://github.com/DanielLMcGuire/Source-Search/releases/download/1.2.5/sourcesearch-1.2.5-1-any.pkg.tar.zst';
            break;
        case 'appimage':
            downloadUrl = 'https://github.com/DanielLMcGuire/Source-Search/releases/download/1.2.5/sourcesearch-x86_64-1.2.5.AppImage';
            break;
        default:
            downloadUrl = '../404.html'; // Default or error URL
            break;
    }
    showCountdownPopup(() => {
        window.location.href = downloadUrl; // Start the download
    });
}

function downloadWindows() {
    showCountdownPopup(() => {
        window.location.href = "https://github.com/DanielLMcGuire/Source-Search/releases/download/1.2.5/sourcesearchsetup-x86_64-1.2.5.exe"; // Replace with your actual Windows download URL
    });
}

function showComingSoon() {
    document.getElementById("comingSoonPopup").style.display = "block";
}

function closeComingSoonPopup() {
    document.getElementById("comingSoonPopup").style.display = "none";
}

function sourceCode() {
    window.location.href = "https://github.com/DanielLMcGuire/Source-Search/archive/refs/tags/1.2.5.zip"; // Replace with your actual source code URL
}

function showLinuxPopup() {
    document.getElementById("linuxPopup").style.display = "block";
}

function closeLinuxPopup() {
    document.getElementById("linuxPopup").style.display = "none";
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
