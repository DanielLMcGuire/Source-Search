let countdownTimer;
let countdownValue = 10; // Starting value for countdown

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

function downloadWindows() {
    showCountdownPopup(() => {
        window.location.href = "../dl404.html"; // Replace with your actual download URL
    });
}

function downloadLinux() {
    showCountdownPopup(() => {
        // Insert the Linux download URL
        window.location.href = "../dl404.html"; // Replace with your actual download URL
    });
}

// Similarly, you can update other download functions
