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

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: ChangeState(Lightbulb_Attack)

	elseif agent: GetBoolValue("seeing_entity") then
		if agent: GetStringValue("seen_entity_bp") == "Charge" then
			print ("Chasing charge...")
			agent: SetAnimation("walkAnimation", true, false)
			agent: ChangeState(Lightbulb_Chase)

		elseif agent: GetStringValue("seen_entity_bp") == "Player" then
			print ("Chasing player...")
			agent: SetAnimation("walkAnimation", true, false)
			agent: ChangeState(Lightbulb_Chase)
		end
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

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		print ("Touching player...")
		agent: ChangeState(Lightbulb_Attack)

	elseif agent: GetBoolValue("touching_entity") and agent: GetStringValue("touched_entity_bp") == "Charge" then
		print ("Eating charge...")
		--agent: SetAnimation("eatLightAnimation", true, false)
		agent: ChangeState(Lightbulb_EatCharge)

	elseif not agent:GetBoolValue("seeing_entity") then
		agent: ChangeState(Lightbulb_Alert)

	elseif agent:GetBoolValue("seeing_entity") then
		if not (agent: GetStringValue("seen_entity_bp") == "Player" or agent: GetStringValue("seen_entity_bp") == "Charge") then
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
	wait_time = 5,
	accum_time = 0
}

Lightbulb_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")
	Lightbulb_Alert.accum_time = 0

end

Lightbulb_Alert["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: ChangeState(Lightbulb_Attack)

	elseif agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Player") then
		agent: ChangeState(Lightbulb_Chase)

	elseif agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Charge") then
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

------------------CENTAUR-----------------------

------------------------------------------------
------------------------------------------------

Centaur_Idle = {
}

Centaur_Idle["Enter"] = function(agent)

	print ("[Centaur]: Enter State Idle")

end

Centaur_Idle["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: SetAnimation("killScreamAnimation", false, true)
		agent: ChangeState(Centaur_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_bp") == "Player") then
		agent: SetAnimation("killScreamAnimation", false, false)
		agent: PlayAndDestroySound("CentaurScreeches", 0.5, 0, Vector3(0,0,0), Vector3(0,0,0))
		agent: ChangeState(Centaur_Hold)
	end

end

Centaur_Idle["Exit"] = function(agent)

	print ("[Centaur]: Exit State Idle")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Centaur_Hold = {
	--wait_time = 3,
	--accum_time = 0
}

Centaur_Hold["Enter"] = function(agent)

	print ("[Centaur]: Enter State Hold")
	--Centaur_Hold.accum_time = 0

end

Centaur_Hold["Execute"] = function(agent, msecs)

	--[[if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		SetBoolValue("killScreamAnimationFinish", false)
		agent: ChangeState(Centaur_Attack)
	
	else
		Centaur_Hold.accum_time = Centaur_Hold.accum_time + msecs

		if Centaur_Hold.accum_time >= Centaur_Hold.wait_time then
			Centaur_Hold.accum_time = 0
			--SetAnimation("runAnimation", false, false)
			agent: ChangeState(Centaur_Charge)
		end
	end]]

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: SetAnimation("killScreamAnimation", false, true)
		agent: ChangeState(Centaur_Attack)
	end

	if agent: GetBoolValue("killScreamAnimationFinish") then
		agent: SetAnimation("preparationAnimation", false, false)
		agent: SetBoolValue("killScreamAnimationFinish", false)
	end

	if agent: GetBoolValue("preparationAnimationFinish") then
		agent: SetAnimation("startRunAnimation", false, false)
		agent: SetBoolValue("preparationFinish", false)
		agent: ChangeState(Centaur_Charge)
	end

end

Centaur_Hold["Exit"] = function(agent)

	print ("[Centaur]: Exit State Hold")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Centaur_Charge = {
	component = "CCharger"
}

Centaur_Charge["Enter"] = function(agent)

	print ("[Centaur]: Enter State Charge")
	agent: Activate(Centaur_Charge.component)

end

Centaur_Charge["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Player") then
		agent: SetAnimation("killScreamAnimation", false, true)
		agent: ChangeState(Centaur_Attack)
	end

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_bp") == "Wall") then
		agent: SetAnimation("deathAnimation", false, true)
		agent: ChangeState(Centaur_Die)
	end

	if agent: GetBoolValue("startRunAnimationFinish") then
		agent: SetAnimation("runAnimation", true, false)
		agent: SetBoolValue("startRunAnimationFinish", false)
	end

end

Centaur_Charge["Exit"] = function(agent)

	print ("[Centaur]: Exit State Charge")
	agent: Deactivate(Centaur_Charge.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Centaur_Attack = {
	component = "CAttack"
}

Centaur_Attack["Enter"] = function(agent)

	print ("[Centaur]: Enter State Attack")
	agent: Activate(Centaur_Attack.component)

end

Centaur_Attack["Execute"] = function(agent, msecs)

end

Centaur_Attack["Exit"] = function(agent)

	print ("[Centaur]: Exit State Attack")
	agent: Deactivate(Centaur_Attack.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Centaur_Die = {

}

Centaur_Die["Enter"] = function(agent)

	print ("[Centaur]: Enter State Die")

end

Centaur_Die["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("deathAnimationFinish") then
		agent: SetBoolValue("deathAnimationFinish", false)
		print ("MATAR AL CENTAURO")
		agent: Destroy()
	end
end

Centaur_Die["Exit"] = function(agent)

	print ("[Centaur]: Exit State Die")

end