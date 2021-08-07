const mongoose = require('mongoose');

module.exports = mongoose.model('datos', mongoose.Schema({
  humidity: {
    type: Number,
    required: true
  },
  temperature: {
    type: Number,
    required: true
  },
  floorhumidity0: {
    type: Number,
    required: true
  },
  floorhumidity1: {
    type: Number,
    required: true
  },
  floorhumidity2: {
    type: Number,
    required: true
  },
  fHPercentages0: {
    type: Number,
    required: true
  },
  fHPercentages1: {
    type: Number,
    required: true
  },
  fHPercentages2: {
    type: Number,
    required: true
  },
  timeStamp: {
    type: Date,
    default: Date.now    
  },
  deleted: {
    type: Boolean,
    default: false
  },
}));
