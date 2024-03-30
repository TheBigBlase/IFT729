document.addEventListener("DOMContentLoaded", function() {
    var submitButton = document.getElementById('submitGuess');
    submitButton.addEventListener('click', function() {
        var guessInput = document.getElementById('guessInput').value;
        console.log("La réponse soumise est :", guessInput);
    });
});