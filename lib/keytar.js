'use strict';

const {
  getFreeMem,
} = process.binding('keytar');

getFreeMem[Symbol.toPrimitive] = () => getFreeMem();

module.exports = {
  freemem: getFreeMem,
};
