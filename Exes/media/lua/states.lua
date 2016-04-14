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

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_name") == "Player_Body") then
		agent: ChangeState(State_Chase)
	end

	--if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		--agent: ChangeState(State_Attack)
	--end

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
	agent: Activate(State_Chase["Component"])

end

State_Chase["Execute"] = function(agent)

	if not agent: GetBoolValue("seeing_entity") or (agent: GetBoolValue("seeing_entity") and not agent: GetStringValue("seen_entity_name") == "Player_Body")then
		agent: ChangeState(State_Patrol)
	end

end

State_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")
	agent: Deactivate(State_Chase["Component"])

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Alert = {}

State_Alert["Component"] = "CAlert"

State_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")

end

State_Alert["Execute"] = function(agent)

	print ("[Lua]: Executing State Alert")

end

State_Alert["Exit"] = function(agent)

	print ("[Lua]: Exit State Alert")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Attack = {}

State_Attack["Component"] = "CAttack"

State_Attack["Enter"] = function(agent)

	print ("[Lua]: Enter State Attack")

end

State_Attack["Execute"] = function(agent)

	print ("[Lua]: Executing State Attack")

end

State_Attack["Exit"] = function(agent)

	print ("[Lua]: Exit State Attack")

end
