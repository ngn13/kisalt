FROM alpine as build

RUN apk update && apk upgrade
RUN apk add --no-cache build-base wget boost-dev openssl-dev jsoncpp-dev 

WORKDIR       /app
COPY src      ./src
COPY static   ./static
COPY Makefile ./

# https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=crow
RUN wget https://github.com/CrowCpp/crow/releases/download/v1.0+5/crow-v1.0+5.tar.gz
RUN mkdir crow
RUN mkdir -p /usr/local/include
RUN mkdir -p /usr/local/lib
RUN tar xf crow-v1.0+5.tar.gz -C crow 

WORKDIR /app/crow
RUN cp -r include /usr/local
RUN cp -r lib /usr/local

WORKDIR /app
RUN make && rm -r crow

FROM alpine as main
COPY --from=build /app /
EXPOSE 8080 
RUN apk add --no-cache libstdc++ libgcc libcrypto3 jsoncpp 
ENTRYPOINT ["/kisalt"]
