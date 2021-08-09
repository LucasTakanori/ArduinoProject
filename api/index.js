
const path = require('path');

const express = require('express');
const app = express();
const port = 3000;
const mongoose = require('mongoose');

mongoose.connect('mongodb://localhost:27017/tvshows', {useNewUrlParser: true});
//parse JSON using express
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.use(express.static(__dirname + '/public'));

app.use('/data', require('./routes/data'));

app.get('/', (req, res) => {
    // simple as fuck
    res.sendFile(path.join(__dirname, 'views/index.html'));
});

// let datos = [
//     {
//     humidity: '66',
//     temperature: '26.5',
//     floorhumidity0: '351',
//     floorhumidity1: '352',
//     floorhumidity2: '343',s
//     fHPercentages0: '81',
//     fHPercentages1: '82',
//     fHPercentages2: '88',
//     timeStamp: '2021-05-20T15:07:41.932+00:00'
// },
// {
    // humidity: '75',
    // temperature: '23.1',
    // floorhumidity0: '100',
    // floorhumidity1: '200',
    // floorhumidity2: '300',
    // fHPercentages0: '20',
    // fHPercentages1: '40',
    // fHPercentages2: '60',
//     timeStamp: '2021-05-20T15:07:41.932+00:00'
// },
// ];

//set the server to listen at port 

app.listen(port, () => console.log(`Server listening at port ${port}`))

