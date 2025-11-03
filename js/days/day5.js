// Number to words mapping
const wordMap = new Map([
    [1, "One"], [2, "Two"], [3, "Three"], [4, "Four"], [5, "Five"],
    [6, "Six"], [7, "Seven"], [8, "Eight"], [9, "Nine"], [10, "Ten"],
    [11, "Eleven"], [12, "Twelve"], [13, "Thirteen"], [14, "Fourteen"],
    [15, "Fifteen"], [16, "Sixteen"], [17, "Seventeen"], [18, "Eighteen"],
    [19, "Nineteen"], [20, "Twenty"], [30, "Thirty"], [40, "Forty"],
    [50, "Fifty"], [60, "Sixty"], [70, "Eeventy"], [80, "Eighty"],
    [90, "Ninety"]
]);

function numberToWords(n) {
     // Input validation
    if (!Number.isInteger(n) || n < 1) {
        throw new Error("Please enter a positive integer");
    }

    if(n > 10**15){
        throw new Error("Number too large.");
    }

    if(n === 1000) return "One Thousand";

    if(n < 20) return wordMap.get(n);

    if(n < 100){
        const tens = Math.floor(n / 10) * 10;
        const units = n % 10;
        return wordMap.get(tens) + (units ? " " + wordMap.get(units) : "");
    }

    if(n < 1000){
        const hundreds = Math.floor(n / 100);
        const remainder = n % 100;
        return wordMap.get(hundreds) + " Hundred " + 
            (remainder ? " and " + numberToWords(remainder) : "");
    }

    const scales = ["", "Thousand", "Million", "Billion", "Trillion"];
    let scaleIndex = 0;
    let result = "";

    while(n > 0){
        const chunk = n % 1000;
        if(chunk != 0){
            const chunkWords = numberToWords(chunk);
            const scale = scales[scaleIndex];
            result = chunkWords + (scale ? " " + scale : "") + (result ? " " + result : "");
        }
        n = Math.floor(n / 1000);
        scaleIndex++;
    }

    return result;
}

function countLetters(str){
    return str.replace(/[^\w]/g, "").length;
}

function compute(){
    try{
        const n = parseInt(document.getElementById('nInput').value);
        if(isNaN(n) || n < 1){
            alert("Please enter a positive integer");
            return;
        }

        const words = numberToWords(n);
        const count = countLetters(words);

        document.getElementById('inWords').textContent = words;
        document.getElementById('letterCount').textContent = 
        `Letter count : ${count}`;
    } catch(error){
        alert(error.message);
    }
}