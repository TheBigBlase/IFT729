document.addEventListener("DOMContentLoaded", function() {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');

    // Variable pour suivre si le bouton de la souris est enfoncé
    let isDrawing = false;

    canvas.addEventListener('mousedown', function(event) {
        // Le bouton de la souris est enfoncé, commencez à dessiner
        isDrawing = true;
        // Commencez à dessiner à la position initiale
        draw(event);
    });

    canvas.addEventListener('mousemove', function(event) {
        // Si le bouton de la souris est enfoncé, continuez à dessiner
        if (isDrawing) {
            draw(event);
        }
    });

    canvas.addEventListener('mouseup', function() {
        // Le bouton de la souris est relâché, arrêtez de dessiner
        isDrawing = false;
    });


    function draw(event) {
        const rect = canvas.getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;

         // Couleur bleue
        const newColor = [0, 0, 255, 255];

        // Mettre à jour la couleur du pixel
        const padding = 3; // pour rendre visible l'endroit cliqué
        for (let abs = x-padding; abs < x+padding; abs++) {
            for (let ord = y-padding; ord < y+padding; ord++) {
                let pixelData = ctx.getImageData(abs, ord, 1, 1);
                for (let i = 0; i < 4; i++) {
                    pixelData.data[i] = newColor[i];
                }
                // Mettre à jour l'affichage
                ctx.putImageData(pixelData, abs, ord);
            }
        }

        console.log(`Coordonnées du pixel cliqué : (${x}, ${y})`);
    }
});