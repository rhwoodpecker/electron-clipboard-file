# electron-clipboard-file
`c++ nodejs addon`，在 `electron` 应用中， `mac` 平台实现文件复制到剪贴板功能

## Install
`npm install electron-clipboard-file`
## Usage
```js
const copyFileToClipboard = require('electron-clipboard-file')
copyFileToClipboard('User/Renhao/Desktop/hello.txt')
```

## Props
| 名称     | 说明                 | 类型                                   | 是否必选 |
| -------- | -------------------- | -------------------------------------- | -------- |
| filePath | 要拷贝的文件完整路径 | `string`                               | 是       |
## Description
仅供学习使用
