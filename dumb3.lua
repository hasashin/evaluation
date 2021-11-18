--dumb3.lua
counter = 0
function dumb3whatTo( agent, actorKnowledge, time)
   if ( actorKnowledge:isMoving()) then
   	dist = actorKnowledge:getLongDestination()
        io.write( "I'm going. Destination: ")
	showVector( dist)
	io.write( "\t")
	showVector( actorKnowledge:getShortDestination())
	io.write( "\n")
   else
	if ( time > 50) then
		agent:moveTo( Vector4d( 40, 40, 0, 0))   
 	end
   end
end;

function dumb3onStart( agent, actorKnowledge, time)
   io.write( counter)
   io.write( "My name is: ", actorKnowledge:getName(), "\n")
end

function showVector( vector)
    io.write( "(", vector:value(0), ",", vector:value(1), ",", vector:value(2), ",", vector:value(3),");")
end;