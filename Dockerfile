FROM --platform=linux/amd64 golang:alpine as builder

WORKDIR /app

COPY . .

RUN CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -o COD9000

FROM --platform=linux/amd64 alpine

WORKDIR /app

COPY --from=builder /app/COD9000 .

EXPOSE 3000

ENTRYPOINT [ "/app/COD9000" ]