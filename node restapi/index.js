const express = require('express');

const app = express();
const port = 3000;

//parse JSON using express
app.use(express.json());
app.use(express.urlencoded({ extended: false}));


let datos = [
    {
    humidity: '66',
    temperature: '26.5',
    floorhumidity0: '351',
    floorhumidity1: '352',
    floorhumidity2: '343',
    fHPercentages0: '81',
    fHPercentages1: '82',
    fHPercentages2: '88',
    date:'2020-09-04',
    time: '12:48',
},
{
    humidity: '75',
    temperature: '23.1',
    floorhumidity0: '100',
    floorhumidity1: '200',
    floorhumidity2: '300',
    fHPercentages0: '20',
    fHPercentages1: '40',
    fHPercentages2: '60',
    date:'2020-09-05',
    time: '13:00', 
},
];

// get the data list in the form of JSON
app.get('/data', (req, res) => {
    res.json(datos);
})

//ad data to the list
app.post('/data', (req, res) => {
    const data = req.body

    console.log(data);
    datos.push(data);
    res.send('data is added to the list!');
})

// seartch for a data
app.get('/data/:id', (req, res) => {
    const id = req.params.id

    for(let data of datos) {
        if(data.id === id) {
            res.json(data);
            console.log(data);
            return
        }
    }

    res.status(404).send("data not found");
})

//remove data from the list
app.delete('/data/:id', (req, res) => {
    const id = req.params.id;

    datos = datos.filter((data) => {
        if(data.id !== id) {
            return true;
        }
        return false;
    })

    res.send('data is deleted')
})
//set the server to listen at port 

app.listen(port, () => console.log(`Server listening at port ${port}`))

