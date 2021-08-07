const express = require('express');
const router = express.Router();

const DatoSchema = require('./../models/dato');

// get the data list which aren't deleted
router.get('/', (req, res) => {
    DatoSchema.find({ "deleted": false }, (err, data) => {
        if (err) {
            res.send({ error: err });
            return;
        }
        res.send(data);
    })

});

//get by id
router.get('/:id', (req, res) => {
    DatoSchema.findById(req.params.id, (err, data) => {
        if (err) {
            res.send({ error: err });
            return;
        }
        res.send(data);
    })

});

router.get('/date/:start/:end', (req, res) => {
    const startDate = new Date(req.params.start);
    const endDate = new Date(new Date(req.params.end).getTime()+(1*24*60*60*1000)); // First number is to specify the number of days to be added

    console.log(endDate);

    DatoSchema.find({ "deleted": false, timeStamp: { $gte: startDate, $lte: endDate }, }, req.params.property, (err, data) => {
        if (err) {
            res.send({ error: err });
            return;
        }
        res.send(data);
    })
});

router.get('/prop/:property', (req, res) => {
    DatoSchema.find({ "deleted": false }, req.params.property, (err, data) => {
        if (err) {
            res.send({ error: err });
            return;
        }
        res.send(data);
    })
});



//ad data to the list
router.post('/', (req, res) => {
    const data = req.body
    const dato = new DatoSchema(data);

    dato.save(err => {
        if (err) {
            res.send({ error: err, message: 'Error saving the data' });
            return;
        }
        res.status(200).send({ message: 'Data added to the database successfully :)!' });
    });
    console.log(data);
});

//remove data from the list
router.delete('/:id', (req, res) => {

    DatoSchema.findByIdAndUpdate(req.params.id, { "deleted": true }, (err, data) => {
        if (err) return res.send({ error: err });
        res.send("Item deleted");
    });
});

module.exports = router;