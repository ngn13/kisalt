# kisalt | simple link shortener
![](https://img.shields.io/github/license/ngn13/kisalt)
![](https://img.shields.io/github/repo-size/ngn13/kisalt)
![](https://img.shields.io/github/actions/workflow/status/ngn13/kisalt/publish.yml)

kisalt is a dead simple link shortener written with in C++ using the [Crow](https://github.com/CrowCpp/Crow) web framework.

### Deploy
You can easily deploy the app with docker and place it behind a proxy:
```bash
docker run -d --restart=unless-stopped \
     -p 127.0.0.1:8080:8080            \
     -e URL=https://k.example.com      \
     -v $PWD/data:/data                \
     ghcr.io/ngn13/kisalt
```
Change the `URL` accordingly. 

To disable the saving the links, you can use the `NOSAVE` option.
A volume is not needed when using this option:
```bash
docker run -d --restart=unless-stopped \
    -p 127.0.0.1:8080:8080             \
    -e URL=https://k.example.com       \
    -e NOSAVE=1                        \
    ghcr.io/ngn13/kisalt
```

### Usage
You can use the web interface to shorten links, or you can directly use the API:
```bash
curl https://k.example.com/add\?url=<url>
```
