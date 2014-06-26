


sp::weak_ptr<neb::core::shape::base>                                    phx::core::actor::base::createShapeBox(glm::vec3 size) {

	auto self(isActorRigidActor());

	auto shape = sp::make_shared<neb::final::gfx_core::core::shape::box>(self);

	neb::core::shape::util::parent::insert(shape);

	return shape;
}    
