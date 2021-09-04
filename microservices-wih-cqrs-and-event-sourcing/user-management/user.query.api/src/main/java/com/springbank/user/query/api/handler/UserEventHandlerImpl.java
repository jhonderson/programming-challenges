package com.springbank.user.query.api.handler;

import com.springbank.user.core.event.UserRegisteredEvent;
import com.springbank.user.core.event.UserRemovedEvent;
import com.springbank.user.core.event.UserUpdatedEvent;
import com.springbank.user.query.api.repository.UserRepository;
import org.axonframework.config.ProcessingGroup;
import org.axonframework.eventhandling.EventHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
@ProcessingGroup("user-group")
public class UserEventHandlerImpl implements UserEventHandler {
    private final UserRepository userRepository;

    @Autowired
    public UserEventHandlerImpl(final UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @EventHandler
    @Override
    public void on(UserRegisteredEvent event) {
        userRepository.save(event.getUser());
    }

    @EventHandler
    @Override
    public void on(UserUpdatedEvent event) {
        userRepository.save(event.getUser());
    }

    @EventHandler
    @Override
    public void on(UserRemovedEvent event) {
        userRepository.deleteById(event.getId());
    }
}
