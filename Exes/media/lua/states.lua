------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Patrol = {}

State_Patrol["Component"] = "CPatrol"

State_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")
	agent: Activate(State_Patrol["Component"])

end

State_Patrol["Execute"] = function(agent)

	if agent: GetBoolValue("SeeingPlayer") then
		agent: ChangeState(State_Chase)
	end

end

State_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")
	agent: Deactivate(State_Patrol["Component"])

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Chase = {}

State_Chase["Component"] = "CChase"

State_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")

end

State_Chase["Execute"] = function(agent)

	--if not agent: GetBoolValue("SeeingPlayer") then
	if not agent: GetBoolValue("SeeingPlayer") then
		agent: ChangeState(State_Patrol)
	end

end

State_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")

end
