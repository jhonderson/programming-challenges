package com.springbank.user.query.api.handler;

import com.springbank.user.query.api.query.FindAllUsersQuery;
import com.springbank.user.query.api.query.FindUserByIdQuery;
import com.springbank.user.query.api.query.SearchUsersQuery;

public interface UserQueryHandler {
    UserQueryResult getUserById(FindUserByIdQuery findUserByIdQuery);
    UserQueryResult searchUsers(SearchUsersQuery searchUsersQuery);
    UserQueryResult getAllUsers(FindAllUsersQuery findAllUsersQuery);
}
