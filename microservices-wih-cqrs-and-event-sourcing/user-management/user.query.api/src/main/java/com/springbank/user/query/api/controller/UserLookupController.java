package com.springbank.user.query.api.controller;

import com.springbank.user.query.api.dto.UserLookupResponse;
import com.springbank.user.query.api.handler.UserQueryResult;
import com.springbank.user.query.api.query.FindAllUsersQuery;
import com.springbank.user.query.api.query.FindUserByIdQuery;
import com.springbank.user.query.api.query.SearchUsersQuery;
import lombok.extern.slf4j.Slf4j;
import org.axonframework.messaging.responsetypes.ResponseTypes;
import org.axonframework.queryhandling.QueryGateway;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/v1/user-search")
@Slf4j
public class UserLookupController {
    private final QueryGateway queryGateway;

    @Autowired
    public UserLookupController(final QueryGateway queryGateway) {
        this.queryGateway = queryGateway;
    }

    @GetMapping("/")
    @PreAuthorize("hasAuthority('READ_PRIVILEGE')")
    public ResponseEntity<UserLookupResponse> getAllUsers() {
        final UserQueryResult response;
        try {
            response = queryGateway.query(new FindAllUsersQuery(),
                    ResponseTypes.instanceOf(UserQueryResult.class)).join();
        } catch (final Exception e) {
            log.error(e.getMessage(), e);
            return new ResponseEntity<>(new UserLookupResponse("Failed to complete get all users request"),
                    HttpStatus.INTERNAL_SERVER_ERROR);
        }
        if (response == null || response.getUsers() == null) {
            return new ResponseEntity<>(null, HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<>(new UserLookupResponse(response.getUsers()), HttpStatus.OK);
    }

    @GetMapping("/{id}")
    @PreAuthorize("hasAuthority('READ_PRIVILEGE')")
    public ResponseEntity<UserLookupResponse> getUserById(@PathVariable("id") final String id) {
        final UserQueryResult response;
        try {
            response = queryGateway.query(new FindUserByIdQuery(id),
                    ResponseTypes.instanceOf(UserQueryResult.class)).join();
        } catch (final Exception e) {
            log.error(e.getMessage(), e);
            return new ResponseEntity<>(new UserLookupResponse("Failed to complete get user by id request for id " + id),
                    HttpStatus.INTERNAL_SERVER_ERROR);
        }
        if (response == null || response.getUsers() == null) {
            return new ResponseEntity<>(null, HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>(new UserLookupResponse(response.getUsers()), HttpStatus.OK);
    }

    @GetMapping("/search/{filter}")
    @PreAuthorize("hasAuthority('READ_PRIVILEGE')")
    public ResponseEntity<UserLookupResponse> searchUserByFilter(@PathVariable("filter") final String filter) {
        final UserQueryResult response;
        try {
            response = queryGateway.query(new SearchUsersQuery(filter),
                    ResponseTypes.instanceOf(UserQueryResult.class)).join();
        } catch (final Exception e) {
            log.error(e.getMessage(), e);
            return new ResponseEntity<>(new UserLookupResponse("Failed to complete search users request for filter " + filter),
                    HttpStatus.INTERNAL_SERVER_ERROR);
        }
        if (response == null || response.getUsers() == null) {
            return new ResponseEntity<>(null, HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<>(new UserLookupResponse(response.getUsers()), HttpStatus.OK);
    }
}
