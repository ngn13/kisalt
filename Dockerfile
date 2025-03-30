# build the binary
FROM alpine as builder

RUN apk update && apk upgrade
RUN apk add --no-cache build-base wget asio asio-dev openssl-dev jsoncpp-dev

WORKDIR       /app
COPY inc      ./inc
COPY src      ./src
COPY static   ./static
COPY Makefile ./

WORKDIR /app
RUN make
RUN rm -r src
RUN rm -r inc

# run the binary
FROM alpine as ruuner

COPY --from=builder /app /
RUN apk add --no-cache libstdc++ libgcc libcrypto3 jsoncpp asio

EXPOSE 8080
ENTRYPOINT ["/kisalt"]
