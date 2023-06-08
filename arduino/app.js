

function spasi()
        {
            vlagaZemlje=Number(document.getElementById('vlagaInput').value);
            dugme=Number(document.getElementById('btn').value); 
            firebase.database().ref('Parametri').set({
                parametarVlaga: vlagaZemlje,
                parametarDugme: dugme,
                    }, (error) => {
                        if (error) {
                    console.log("Greska u snimanju podataka!");
                            } else {
                    console.log("Uspjesno snimljeni podaci!");
                }
});
        }
  

        function upali()
        {
            vlagaZemlje=90;
            dugme=1; 
            firebase.database().ref('Parametri').set({
                parametarVlaga: vlagaZemlje,
                parametarDugme: dugme,
                    }, (error) => {
                        if (error) {
                    console.log("Greska u snimanju podataka!");
                            } else {
                    console.log("Uspjesno snimljeni podaci!");
                }
});
        }