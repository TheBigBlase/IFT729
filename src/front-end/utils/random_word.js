document.addEventListener("DOMContentLoaded", function() {

    // Liste de mots
    var mots = ["pomme", "Tour Eiffel", "Canada", "voiture", "maison", "fromage"];

    // Fonction pour tirer un mot aléatoire
    function tirerMotAleatoire(listeMots) {
        var indexAleatoire = Math.floor(Math.random() * listeMots.length);
        return listeMots[indexAleatoire];
    }

    // Tirer un mot aléatoire
    var motAleatoire = tirerMotAleatoire(mots);

    // Afficher le mot aléatoire dans l'élément HTML
    var wordToGuessElement = document.getElementById('wordToGuess');
    wordToGuessElement.textContent = motAleatoire;
});
