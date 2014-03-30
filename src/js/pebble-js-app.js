Pebble.addEventListener("ready",
function(e) {
    console.log("Hello world! - Sent from your javascript application.");
}
);

Pebble.addEventListener("appmessage",
function(e) {
    
    var toMail="ngmuley@ncsu.edu";
    var toName="Naman";
    var fromMail="info@sendgridcharge.com";
    var subject="sendGridCharge Notification";
    var sendGriduser="xxxxxx"
    var sendGridpass="xxxxxx"

    if (e.payload.myInt){
        console.log("battery status changed");
        var req = new XMLHttpRequest();
        var body = "your charger was attached/detached";
        req.open('POST', 'https://api.sendgrid.com/api/mail.send.json', true);
        req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        req.send("api_user="+sendGriduser+"&api_key="+sendGridpass+"&to=" + toMail + "&toname="+toName+"&subject="+subject+"&text="+body+"&from="+fromMail)
        req.onload = function (f){
           if(req.status == 200){
                console.log("SENT");
           } 
        }
    }else if(e.payload.battlow){
        console.log("battery low");
        var req = new XMLHttpRequest();
        var body = "your battery is lower than 20%";
        req.open('POST', 'https://api.sendgrid.com/api/mail.send.json', true);
        req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        req.send("api_user="+sendGriduser+"&api_key="+sendGridpass+"&to="+toMail+"&toname="+toName+"&subject="+subject+"&text="+body+"&from="+fromMail)
        req.onload = function (f){
           if(req.status == 200){
                console.log("SENT");
           } 
        }    
   // console.log("sent email using sendgrid");
    }else if(e.payload.selectClick){
        console.log("Select button clicked");
        var req = new XMLHttpRequest();
        var body = "the battery level of your pebble watch is: "+ e.payload.selecClick +"%";
        req.open('POST', 'https://api.sendgrid.com/api/mail.send.json', true);
        req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        req.send("api_user="+sendGriduser+"&api_key="+sendGridpass+"&to="+toMail+"&toname="+toName+"&subject="+subject+"&text="+body+"&from="+fromMail)
        req.onload = function (f){
           if(req.status == 200){
                console.log("SENT");
           } 
        }    
    }

}
);


