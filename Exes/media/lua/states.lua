------------------------------------------------
------------------------------------------------

------------------CRAWLER-----------------------

------------------------------------------------
------------------------------------------------

Crawler_Patrol = {
	component = "CPatrol"
}

Crawler_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")
	agent: Activate(Crawler_Patrol.component)

end

Crawler_Patrol["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: ChangeState(Crawler_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Player") then
		agent: ChangeState(Crawler_Chase)
	end

end

Crawler_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")
	agent: Deactivate(Crawler_Patrol.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Chase = {
	component = "CChase"
}

Crawler_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")
	agent: Activate(Crawler_Chase.component)

end

Crawler_Chase["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: ChangeState(Crawler_Attack)
	end

	if not agent: GetBoolValue("seeing_entity") or (agent: GetBoolValue("seeing_entity") and not agent: GetStringValue("seen_entity_bp") == "Player")then
		agent: ChangeState(Crawler_Alert)
	end

end

Crawler_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")
	agent: Deactivate(Crawler_Chase.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Alert = {
	component = "CAlert",
	wait_time = 5000,
	accum_time = 0
}

Crawler_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")
	Crawler_Alert.accum_time = 0

end

Crawler_Alert["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: ChangeState(Crawler_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Player") then
		agent: ChangeState(Crawler_Chase)
	end

	Crawler_Alert.accum_time =  Crawler_Alert.accum_time + msecs

	if Crawler_Alert.accum_time >= Crawler_Alert.wait_time then
		Crawler_Alert.accum_time = 0
		agent: ChangeState(Crawler_Patrol)
	end

end

Crawler_Alert["Exit"] = function(agent)

	print ("[Lua]: Exit State Alert")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Attack = {
	component = "CAttack"
}

Crawler_Attack["Enter"] = function(agent)

	print ("[Lua]: Enter State Attack")
	agent: Activate(Crawler_Attack.component)

end

Crawler_Attack["Execute"] = function(agent, msecs)

	--print ("[Lua]: Executing State Attack")

end

Crawler_Attack["Exit"] = function(agent)

	print ("[Lua]: Exit State Attack")
	agent: Deactivate(Crawler_Attack.component)

end



------------------------------------------------
------------------------------------------------

-----------------LIGHTBULB----------------------

------------------------------------------------
------------------------------------------------

Lightbulb_Patrol = {
	component = "CPatrol"
}

Lightbulb_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")
	agent: Activate(Lightbulb_Patrol.component)

end

Lightbulb_Patrol["Execute"] = function(agent, msecs)

	--if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		--agent: ChangeState(Lightbulb_Attack)
	--end

	if agent: GetBoolValue("seeing_entity") then
		if agent: GetStringValue("seen_entity_bp") == "Charge" then
			print ("Chasing charge...")
			agent: ChangeState(Lightbulb_Chase)
		end

		--if agent: GetStringValue("seen_entity_bp") == "Player" then
			--print ("Chasing player...")
			--agent: ChangeState(Lightbulb_Chase)
		--end
	end

end

Lightbulb_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")
	agent: Deactivate(Lightbulb_Patrol.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Lightbulb_Chase = {
	component = "CChase"
}

Lightbulb_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")
	agent: Activate(Lightbulb_Chase.component)

end

Lightbulb_Chase["Execute"] = function(agent, msecs)

	--if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		--print ("Touching player...")
		--agent: ChangeState(Lightbulb_Attack)
	--end

	if agent: GetBoolValue("touching_entity") and agent: GetStringValue("touched_entity_bp") == "Charge" then
		print ("Eating charge...")
		agent: ChangeState(Lightbulb_EatCharge)

	elseif not agent:GetBoolValue("seeing_entity") then
		agent: ChangeState(Lightbulb_Alert)

	elseif agent:GetBoolValue("seeing_entity") then
		--if not agent: GetStringValue("seen_entity_bp") == "Player" then
			--agent: ChangeState(Lightbulb_Alert)
		--end

		if not agent: GetStringValue("seen_entity_bp") == "Charge" then
			agent: ChangeState(Lightbulb_Alert)
		end
	end

end

Lightbulb_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")
	agent: Deactivate(Lightbulb_Chase.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Lightbulb_Alert = {
	component = "CAlert",
	wait_time = 5000,
	accum_time = 0
}

Lightbulb_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")
	Lightbulb_Alert.accum_time = 0

end

Lightbulb_Alert["Execute"] = function(agent, msecs)

	--if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		--agent: ChangeState(Lightbulb_Attack)
	--end

	--if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Player") then
		--agent: ChangeState(Lightbulb_Chase)
	--end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Charge") then
		agent: ChangeState(Lightbulb_Chase)
	else
		Lightbulb_Alert.accum_time = Lightbulb_Alert.accum_time + msecs

		if Lightbulb_Alert.accum_time >= Lightbulb_Alert.wait_time then
			Lightbulb_Alert.accum_time = 0
			agent: ChangeState(Lightbulb_Patrol)
		end
	end

end

Lightbulb_Alert["Exit"] = function(agent)

	print ("[Lua]: Exit State Alert")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Lightbulb_Attack = {
	component = "CAttack"
}

Lightbulb_Attack["Enter"] = function(agent)

	print ("[Lua]: Enter State Attack")
	agent: Activate(Lightbulb_Attack.component)

end

Lightbulb_Attack["Execute"] = function(agent, msecs)

	--print ("[Lua]: Executing State Attack")

end

Lightbulb_Attack["Exit"] = function(agent)

	print ("[Lua]: Exit State Attack")
	agent: Deactivate(Lightbulb_Attack.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Lightbulb_EatCharge = {
	component = "CEater"
}

Lightbulb_EatCharge["Enter"] = function(agent)

	print ("[Lua]: Enter State Eat Charge")
	agent: Activate(Lightbulb_EatCharge.component)

end

Lightbulb_EatCharge["Execute"] = function(agent, msecs)

	agent: ChangeState(Lightbulb_Patrol)

end

Lightbulb_EatCharge["Exit"] = function(agent)

	print ("[Lua]: Exit State Eat Charge")
	agent: Deactivate(Lightbulb_EatCharge.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Lightbulb_Wait = {

}

Lightbulb_Wait["Enter"] = function(agent)

	print ("[Lua]: Enter State Wait")

end

Lightbulb_Wait["Execute"] = function(agent, msecs)

	--agent: ChangeState(Lightbulb_Patrol)

end

Lightbulb_Wait["Exit"] = function(agent)

	print ("[Lua]: Exit State Wait")

end
