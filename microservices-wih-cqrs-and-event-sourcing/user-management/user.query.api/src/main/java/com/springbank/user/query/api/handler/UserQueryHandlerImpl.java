package com.springbank.user.query.api.handler;

import com.springbank.user.query.api.query.FindAllUsersQuery;
import com.springbank.user.query.api.query.FindUserByIdQuery;
import com.springbank.user.query.api.query.SearchUsersQuery;
import com.springbank.user.query.api.repository.UserRepository;
import org.axonframework.queryhandling.QueryHandler;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;

@Service
public class UserQueryHandlerImpl implements UserQueryHandler {
    private final UserRepository userRepository;

    @Autowired
    public UserQueryHandlerImpl(final UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @QueryHandler
    @Override
    public UserQueryResult getUserById(final FindUserByIdQuery findUserByIdQuery) {
        return userRepository.findById(findUserByIdQuery.getId())
                .map(UserQueryResult::new)
                .orElse(null);
    }

    @QueryHandler
    @Override
    public UserQueryResult searchUsers(final SearchUsersQuery searchUsersQuery) {
        var users = new ArrayList<>(userRepository.findByFilterRegex(searchUsersQuery.getFilter()));
        return new UserQueryResult(users);
    }

    @QueryHandler
    @Override
    public UserQueryResult getAllUsers(final FindAllUsersQuery findAllUsersQuery) {
        var users = new ArrayList<>(userRepository.findAll());
        return new UserQueryResult(users);
    }
}
