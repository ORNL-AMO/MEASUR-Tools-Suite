const express = require('express')
const app = express()
const port = 3000
const path = require('path');
const process = require('process');
const fs = require('fs');

app.get('/stop', (req, res) => {
  console.log('Stopping..');
  res.send('Stopped');
  console.log('Stopped');
  server.close();  
})

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname + '/wasm-express.html'));
});

app.get('/scriptsList', function(req, res) {
    scriptsList.sort();
    res.json(scriptsList);
});

app.use('/assets', express.static('build-wasm/bin'));
app.use('/jquery', express.static('node_modules/jquery/dist/'));
app.use('/assert', express.static('node_modules/assert-plus'));
app.use('/tests', express.static('tests/wasm/'));
loadStaticFiles('tests/wasm').then();

let scriptsList = [];
async function loadStaticFiles(dir) {
    try {
        const lFiles = await fs.promises.readdir(dir);
        for (const file of lFiles) {
            const stats = await fs.promises.stat(path.join(dir, file));
            if (stats.isDirectory()) {
                if(file === 'wasm-express') continue;
                const dirPath = path.join(dir, file);
                app.use('/tests', express.static(dirPath));
                loadStaticFiles(dirPath).then();
            }
            else if (stats.isFile) {
                if(!file.startsWith('wasm-express')) {
                    scriptsList.push(file);
                }
            }
        }
    } catch (err) {}
}

let server = app.listen(port, () => console.log(`Wasm Testing Served on: localhost:${port}`));

process.on('SIGTERM', () => {
  console.log('SIGTERM received: closing server...');
  server.close(() => {
      console.log('Server closed');
      process.exit(0); 
  });
});

process.on('SIGINT', () => {
  console.log('SIGINT received: closing server...');
  server.close(() => {
      console.log('Server closed');
      process.exit(0);
  });
});