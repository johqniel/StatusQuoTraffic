//
//  test.cpp
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//



// notes:


// 12.05. TODO

// Dijkstra returned die paths quasi in der falschen reihenfolge also von hinten nach vorne.
// gerade wurde eine funktion und zwar updateflowpath dingens so programmiert dass es quasi ind er forschleife dann rückwärts durch den path vector läuft
// wenn das aber mal falsch gemacht wird bei einer funktion die das gleiche machen soll dann kann das zu sehr große verwirrungen führen weil dann im zweifel kanten hinzugefügt werden die nicht da sind und dann blablabla das wäre echt mega kacke. 

// Also es wird mehrere graphen geben auf denen die Agenten den besten weg suchen.

// Einen reinen auto Graph, einen reinen Öffis Graph und einen reinen Fahrrad Graph

// Dann soll es noch die möglichkeit geben dass menschen von den Öffis zum fahrrad oder vom fahrrad zu den öffis oder vom auto zu den öffis wechseln. dafür gibt es dann drei weitere graphen die zeigen aber dann an jedem knoten auch auf den jeweils "cleanen" Öffi bzw fahrrad graphen an genau dem selben knoten. mit einer entsprechenden umstiegzeit/ kosten. (Auto und fahrräder müssten geparkt werden.

// das ganze ist dann intern natürlich ein normaler graph also ein ganzer graph. die start und zielpunkte müssen dann irgendwie für jeden agenten bevor er sucht einmal miteinander geeignet verschränkt werden, damit der agent nicht mehrmals durch den graphen von verschiedenen start und endpunkten aus suchen muss.



// jeder agent hat einen eigenen work knoten und einen home knoten. dadurch wird der graph deutlich größer aber das sollte eigentlich kein problem sein. von seinem home knotenpunkt aus ist der agent zu den entsprechenden home knoten der oben beschriebenen graphen verbunden. dadurch kontrollieren wir auch die umgewöhnungskosten der agenten von der einen commuter methode auf die andere. weil wir ja wissen wen der agent in den einen graph reingeht dann fährt er halt diese art von weg. und naja jeman der bereit ist umzusteigen wird das auch nur tun wenn umsteigen wirlich besser ist.

// wir können dann einfach ablesen welchen weg der agent gegangen ist daran welche kante er am anfang genommen hat. 
