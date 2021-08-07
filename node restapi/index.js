
const express = require('express');
const DatoSchema = require('./models/dato');
const app = express();
const port = 3000;
const mongoose = require('mongoose');

mongoose.connect('mongodb://localhost:27017/tvshows', {useNewUrlParser: true});
//parse JSON using express
app.use(express.json());
app.use(express.urlencoded({ extended: false}));


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

// get the data list which aren't deleted
app.get('/data', (req, res) => {
    DatoSchema.find({"deleted": false}, (err, data) => {
        if(err){
            res.send({error : err });
            return;
        }
        res.send(data);
    })
    
});

//get by id
app.get('/data/:id', (req, res) => {
    DatoSchema.findByID(req.params.id, (err, data) => {
        if(err){
            res.send({error : err });
            return;
        }
        res.send(data);
    })
    
});

app.get('data/:property', (req, res) => {
    DatoSchema.find(req.params.property , (err, data) => {
        if (err || !data) {
            res.send({ error: err });
            return;
        }
        res.send(data);
    });
});



//ad data to the list
app.post('/data', (req, res) => {
    const data = req.body
    const dato = new DatoSchema(data);
    
    dato.save(err => {
        if (err) {
            res.send({ error: err, message: 'Error saving the data' });
            return ;
        }
        res.status(200).send({ message: 'Data added to the database successfully :)!'});
    });
    console.log(data);
});

//remove data from the list
app.delete('/data/:id', (req, res) => {
    
    DatoSchema.findByIdAndUpdate(req.params.id,{"deleted": true} ,(err, data) => {
        if(err) return res.send({ error: err });
        res.send("Item deleted");
    });
});
//set the server to listen at port 

app.listen(port, () => console.log(`Server listening at port ${port}`))

