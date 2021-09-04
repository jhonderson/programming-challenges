package com.springbank.user.cmd.api.controller;

import com.springbank.user.cmd.api.command.UpdateUserCommand;
import com.springbank.user.core.dto.BaseResponse;
import lombok.extern.slf4j.Slf4j;
import org.axonframework.commandhandling.gateway.CommandGateway;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

@RestController
@RequestMapping(path = "/api/v1/user")
@Slf4j
public class UpdateUserController {
    private final CommandGateway commandGateway;

    @Autowired
    public UpdateUserController(final CommandGateway commandGateway) {
        this.commandGateway = commandGateway;
    }

    @PutMapping(path = "/{id}")
    @PreAuthorize("hasAuthority('WRITE_PRIVILEGE')")
    public ResponseEntity<BaseResponse> updateUser(@PathVariable("id") final String id,
                                                   @Valid @RequestBody final UpdateUserCommand command) {
        command.setId(id);
        try {
            this.commandGateway.send(command);
        } catch (final Exception e) {
            log.error(e.getMessage(), e);
            return new ResponseEntity<>(new BaseResponse("Error while processing update user request for id " + id),
                    HttpStatus.INTERNAL_SERVER_ERROR);
        }
        return new ResponseEntity<>(new BaseResponse("User updated"),
                HttpStatus.OK);
    }
}
