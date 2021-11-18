--dumb4.lua
counter = 0
function dumb4whatTo( agent, actorKnowledge, time)
   if ( actorKnowledge:isMoving()) then
   	dist = actorKnowledge:getLongDestination()
        io.write( "I'm going. Destinations:  ")
	showVector( dist)
	io.write( "\t")
	showVector( actorKnowledge:getShortDestination())
	io.write( "\n")
   else
	if ( time > 100) then
		agent:moveTo( Vector4d( 40, 40, 0, 0))   
 	end
   end
   
   enemies = actorKnowledge:getSeenFoes()
   if ( enemies:size() > 0) then
	agent:shootAtPoint( enemies:at(0):getPosition())
   end
end;

function dumb4onStart( agent, actorKnowledge, time)
   io.write( "My name is: ", actorKnowledge:getName(), "\n")
end

function showVector( vector)
    io.write( "(", vector:value(0), ",", vector:value(1), ",", vector:value(2), ",", vector:value(3),");")
end;