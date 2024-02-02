# kisalt | simple link shortener
![](https://img.shields.io/github/license/ngn13/kisalt)
![](https://img.shields.io/tokei/lines/github/ngn13/kisalt)
![](https://img.shields.io/github/actions/workflow/status/ngn13/kisalt/publish.yml)

kisalt is a simple link shortener specifically designed for [PrivateBin](https://github.com/PrivateBin/PrivateBin), but feel free to use it 
however you want

### Install
You can easily deploy the app with docker and place it behind a proxy:
```bash
docker run --restart=unless-stopped \
    -p 127.0.0.1:8080:8080          \
    -e PASSWORD=changeme            \
    -e URL=https://k.example.com    \
    ghcr.io/ngn13/kisalt
```
Change the `PASSWORD` and the `URL` accordingly.

### Usage (with PrivateBin)
Under the `[main]` section of privatebin's `conf.php`, add the following option:
```
urlshortener = "https://k.example.com/add?pwd=changeme&url="
```
again, change the options accordingly.
