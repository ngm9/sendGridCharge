Pebble.addEventListener("ready",
function(e) {
    console.log("Hello world! - Sent from your javascript application.");
}
);

Pebble.addEventListener("appmessage",
function(e) {
    console.log("Pebble battery is: " + e.payload.myInt + "%");
    var req = new XMLHttpRequest();
    req.open('POST', 'https://api.sendgrid.com/api/mail.send.json', true);
    req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    req.send("api_user=namangmuley&api_key=bisnnsendgrid7&to=ngmuley@ncsu.edu&toname=Naman&subject=Example_subject&text=BatterLow&from=info@domain.com")
    req.onload = function (f){
       if(req.status == 200){
            console.log("SENT");
       } 
    }
   // console.log("sent email using sendgrid");

}
);


