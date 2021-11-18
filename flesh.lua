--io.write("Flesh.\n")

mapsize = 400;
destination = Vector4d(mapsize/2,mapsize/2,0,0)
center = Vector4d(mapsize/2,mapsize/2,0,0)

function whatTo(agent, actorKnowledge, gametime)
	--io.write("Flesh entering - What to do?\n")
	if (actorKnowledge:getActionType() == Enumerations.Shooting) or (actorKnowledge:getActionType() == Enumerations.Reloading) then
		--io.write("i")
		agent:continueAction()
		return
	end
	
	--io.write("a")
		foes = actorKnowledge:getSeenFoes()
		if (foes:size() > 0) then
			--io.write("1")
			dist = 999999
			for i = 0, foes:size()-1, 1 do 
				--io.write(".")
				dir = foes:at(i):getPosition() - actorKnowledge:getPosition()
				if dir:length() < dist then
					dist = dir:length()
					closest = foes:at(i)
				end
			end
			if dist < 75 then
				--io.write("2")
				agent:shootAt(closest)
				return
			end
		end
	--io.write(".")
	
	if ((actorKnowledge:getPosition() - center):length() > mapsize/2) 
	or ((actorKnowledge:getPosition() - destination):length() < 10)
	or (actorKnowledge:getActionType() == Enumerations.Waiting)
	then
		--io.write(".")
		destination = Vector4d( agent:randomDouble() * mapsize, agent:randomDouble() * mapsize, 0, 0)
		--io.write(".")
		agent:moveTo(destination)
		--io.write(".")
	else
		--io.write("b")
		agent:continueAction()
		--io.write(".")
	end
	--io.write(".")
	--io.write("\nFlesh exiting - What to do?\n")
end;