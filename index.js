const path = require('path');
const  addon = require(path.join(__dirname, './build/Release/clipboard.node'));


module.exports = function copyFileToClipboard(filePath) {
  const absolutePath = path.resolve(filePath);
  addon.copyFileToClipboard(absolutePath);
};