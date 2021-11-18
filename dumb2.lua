--dumb2.lua
       
p1 = Vector4d(  40,  40, 0, 0)
p2 = Vector4d( 450, 370, 0, 0)
movePoint = p2
       
       
function dumb2whatTo( agent, actorKnowledge, time)
       if ( not actorKnowledge:isMoving()) then
          if ( movePoint == p2) then
            movePoint = p1
          else
            movePoint = p2
          end
          agent:moveTo( movePoint)
       end
     
       showVector( actorKnowledge:getPosition())
                     
       
      -- if (time > 10) then
       --     agent:shootAtPoint( actorKnowledge:getPosition() - Vector4d(10,10,0,0))
       --end
       
       enemies = actorKnowledge:getSeenFoes()
       if ( enemies:size() > 0) then
	       agent:shootAtPoint( enemies:at(0):getPosition())
       end
end

function dumb2onStart( agent, actorKnowledge, time)
   agent:selectWeapon( 1)
end

function showVector( vector)
end;
