FROM alpine as build

RUN apk update && apk upgrade
RUN apk add --no-cache build-base wget asio asio-dev openssl-dev jsoncpp-dev 

WORKDIR       /app
COPY src      ./src
COPY static   ./static
COPY Makefile ./

WORKDIR /app
RUN make && rm -r src

FROM alpine as main
COPY --from=build /app /
EXPOSE 8080 
RUN apk add --no-cache libstdc++ libgcc libcrypto3 jsoncpp asio
ENTRYPOINT ["/kisalt"]
