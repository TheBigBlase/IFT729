document.addEventListener("DOMContentLoaded", function() {
	const word = sessionStorage.getItem("word_to_guess");
	let wordToGuessElement = document.getElementById('wordToGuess');
	wordToGuessElement.textContent = word;
});
