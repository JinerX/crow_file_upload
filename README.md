To work with this project you need to have installed cmake and crow

to setup this project just run `bash setup.sh`
then in the build folder you're going to end up with executable file to run the server

## Testing
To test the server you can use curl
for example
`curl -X POST -d '{"filename": "some_file", "bytes": "1010101110111010"}' http://0.0.0.0:18080/upload` should create a new file in the uploads folder which in hexadecimal spells "abba"
