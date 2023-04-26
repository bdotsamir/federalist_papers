// This test file is in a language I am most familiar with.

// The only reason why this file exists is that I need to make sure that the C code I am writing
// has the correct outputs. If I program it in JavaScript, I can be 100% confident that the C code
// I write is also correct if they have the same output.

const {
    readFileSync
} = require("fs");

const file = readFileSync("../assets/Federalist1.txt").toString();

let everyWord = file.split("Author: Alexander Hamilton")[1].split(" ").map(g => g.trim());
everyWord = everyWord.map(g => g.replaceAll("\n", " "));
let totalLength = 0;
everyWord.forEach(word => totalLength += word.length);

// lol this is terrible
let everySentence = everyWord.join(" ").split(".").map(g => g.trim());
everySentence = everySentence.map(g => g.replaceAll("\n", " "));
let totalSentenceWordCount = 0;
everySentence.forEach(sentence => totalSentenceWordCount += sentence.split(" ").length);

console.log(`Average word length: ${totalLength / everyWord.length}`);
console.log(`Average sentence length: ${totalSentenceWordCount / everySentence.length}`);