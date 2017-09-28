const net = require('net');

const client = net.createConnection({
    port: 23
    , host: '192.168.0.5'
}, () => {
    //'connect' listener
    console.log('connected to server!')
    client.write('world!\r\n')
})
client.on('data', (data) => {
    console.log(data.toString())
    client.end()
})
client.on('end', () => {
    console.log('disconnected from server')
})
client.on('error', (err) => {
    throw err
})
