# kisalt | simple link shortener
![](https://img.shields.io/github/license/ngn13/kisalt)
![](https://img.shields.io/github/repo-size/ngn13/kisalt)
![](https://img.shields.io/github/actions/workflow/status/ngn13/kisalt/publish.yml)

kisalt is a simple link shortener written with [Crow](https://github.com/CrowCpp/Crow)

### Deploy
You can easily deploy the app with docker and place it behind a proxy:
```bash
docker run -d --restart=unless-stopped \
    -p 127.0.0.1:8080:8080             \
    -e URL=https://k.example.com       \
    ghcr.io/ngn13/kisalt
```
Change the `URL` accordingly.

### Usage
You can use the web interface to shorten links, or you can directly use the API:
```bash
curl https://k.example.com/add\?url=<url>
```

### Todo
- Save links to a database
- Better web UI
