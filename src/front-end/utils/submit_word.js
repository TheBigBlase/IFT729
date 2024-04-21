document.addEventListener("DOMContentLoaded", function() {

    let submitButton = document.getElementById('submitGuess');
    submitButton.addEventListener('click', function() {

        let guessInput = document.getElementById('guessInput').value;
        console.log("La réponse soumise est :", guessInput);
		socket.send(`MSSG:${guessInput}:\0`);

        ul = document.getElementById("messageList");
        let li = document.createElement("li");
        li.appendChild(document.createTextNode(guessInput));
        ul.appendChild(li);
    });
});
