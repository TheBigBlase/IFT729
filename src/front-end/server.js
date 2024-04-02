const express = require('express');
const { join } = require('node:path');

const app = express();
const cors = require('cors')

app.use(
  cors({
	  // TODO change that to more precise
	  origin: "*",
  })
)
app.use(express.static(__dirname));

app.get('/drawer', (req, res) => {
  res.sendFile(join(__dirname, 'drawer.html'));
});

app.get('/guesser', (req, res) => {
  res.sendFile(join(__dirname, 'guesser.html'));
});

app.get('/', (req, res) => {
  res.sendFile(join(__dirname, 'index.html'));
});

app.listen(3000, () => {
  console.log('server running at http://localhost:3000');
});
