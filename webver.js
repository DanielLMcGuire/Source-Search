fetch('json/webver.json')
.then(response => response.json())
.then(data => {
    document.getElementById('software-name').textContent = data.name;
    document.getElementById('software-description').textContent = data.description;

    const releaseBar = document.getElementById('release-bar');
    const latestRelease = document.getElementById('latest-release');

    latestRelease.textContent = `Latest Release: ${data.latest.version}`;
    latestRelease.onclick = () => {
        window.open(`release/${data.latest.url}`, '_blank', 'width=1000,height=800');
    };

    data.previous.forEach(release => {
        const li = document.createElement('li');
        const button = document.createElement('button');
        button.textContent = release.version;
        button.onclick = () => {
            window.open(`release/${release.url}`, '_blank', 'width=800,height=600');
        };
        li.appendChild(button);
        releaseBar.appendChild(li);
    });
});
